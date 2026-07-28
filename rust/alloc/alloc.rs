use std::alloc::{alloc, dealloc, Layout};

fn main() {
    let layout = Layout::new::<u16>();
    unsafe {
        let ptr = alloc(layout);
        dealloc(ptr, layout);
    }
}
