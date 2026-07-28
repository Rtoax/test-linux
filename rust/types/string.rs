fn main() {
    let s1 = String::from("hello");
    let s2 = s1;
    // error[E0382]: borrow of moved value: `s1`
    // println!("{}", s1);
    println!("{}", s2);
}
