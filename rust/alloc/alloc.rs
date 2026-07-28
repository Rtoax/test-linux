use std::alloc::{alloc, dealloc, Layout};

fn main() {
    let layout = Layout::new::<u16>();
    let ptr = alloc(layout);
    dealloc(ptr, layout);
}
