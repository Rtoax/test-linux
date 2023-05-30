#include <linux/module.h>
#include <linux/livepatch.h>
#include <linux/fs.h>
#include <linux/time.h>
#include <linux/highuid.h>
#include <linux/pagemap.h>
#include <linux/quotaops.h>
#include <linux/string.h>
#include <linux/buffer_head.h>
#include <linux/writeback.h>
#include <linux/pagevec.h>
#include <linux/mpage.h>
#include <linux/namei.h>
#include <linux/uio.h>
#include <linux/bio.h>
#include <linux/workqueue.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/backing-dev.h>


static void buffer_io_error(struct buffer_head *bh)
{
	printk_ratelimited(KERN_ERR "Buffer I/O error on device %pg, logical block %llu\n",
		bh->b_bdev,
		(unsigned long long)bh->b_blocknr);
}

static void livepatch_ext4_finish_bio(struct bio *bio)
{
	struct bio_vec *bvec;
	struct bvec_iter_all iter_all;

	bio_for_each_segment_all(bvec, bio, iter_all) {
		struct page *page = bvec->bv_page;
#if 0
		struct page *bounce_page = NULL;
#endif
		struct buffer_head *bh, *head;
		unsigned bio_start = bvec->bv_offset;
		unsigned bio_end = bio_start + bvec->bv_len;
		unsigned under_io = 0;
		unsigned long flags;

		if (!page)
			continue;

#if 0
		if (fscrypt_is_bounce_page(page)) {
			bounce_page = page;
			page = fscrypt_pagecache_page(bounce_page);
		}
#endif

		if (bio->bi_status) {
			SetPageError(page);
			mapping_set_error(page->mapping, -EIO);
		}
		bh = head = page_buffers(page);
		/*
		 * We check all buffers in the page under b_uptodate_lock
		 * to avoid races with other end io clearing async_write flags
		 */
		spin_lock_irqsave(&head->b_uptodate_lock, flags);
		do {
			if (bh_offset(bh) < bio_start ||
			    bh_offset(bh) + bh->b_size > bio_end) {
				if (buffer_async_write(bh))
					under_io++;
				continue;
			}
			clear_buffer_async_write(bh);
			if (bio->bi_status)
				buffer_io_error(bh);
		} while ((bh = bh->b_this_page) != head);
		spin_unlock_irqrestore(&head->b_uptodate_lock, flags);
		if (!under_io) {
#if 0
			fscrypt_free_bounce_page(bounce_page);
#endif
			end_page_writeback(page);
		}
	}
}

static struct klp_func funcs[] = {
	{
		.old_name = "ext4_finish_bio",
		.new_func = livepatch_ext4_finish_bio,
	}, { }
};

static struct klp_object objs[] = {
	{
		/* name being NULL means vmlinux */
		.funcs = funcs,
	}, { }
};

static struct klp_patch patch = {
	.mod = THIS_MODULE,
	.objs = objs,
};

static int livepatch_init(void)
{
	int ret;

	ret = klp_enable_patch(&patch);
	if (ret) {
		return ret;
	}
	printk(KERN_INFO "livepatch insert.");
	return 0;
}

static void livepatch_exit(void)
{
	printk(KERN_INFO "livepatch exit.");
}

module_init(livepatch_init);
module_exit(livepatch_exit);
MODULE_LICENSE("GPL");
MODULE_INFO(livepatch, "Y");
