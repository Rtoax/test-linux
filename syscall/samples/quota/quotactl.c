#include <sys/quota.h>
#include <linux/dqblk_xfs.h> /* Definition of Q_X* and XFS_QUOTA_* constants
				(or <xfs/xqm.h>; see NOTES) */

int quotactl(int cmd, const char *special, int id, caddr_t addr);

int main(void)
{
	// TOOD
	return -1;
}
