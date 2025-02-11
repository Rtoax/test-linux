/**
 * ref: https://www.twle.cn/c/yufei/rust/rust-basic-concurrency.html
 */
use std::thread;
use std::time::Duration;

fn main() {
    /* Create thread */
    let handle = thread::spawn(|| {
        for i in 1..10 {
            println!("hi number {} from the spawned thread!", i);
            thread::sleep(Duration::from_millis(1));
        }
    });
    /* Main thread */
    for i in 1..5 {
        println!("hi number {} from the main thread!", i);
        thread::sleep(Duration::from_millis(1));
    }
    handle.join().unwrap();
}
