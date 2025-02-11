fn main() {
    let company_string = "TutorialsPoint";  // string
    let rating_float = 4.5;                 // float
    let is_growing_boolean = true;          // boolean
    let icon_char = '♥';                    // unicode character
    println!("company name is:{}", company_string);
    println!("company rating on 5 is:{}", rating_float);
    println!("company is growing :{}", is_growing_boolean);
    println!("company icon is:{}", icon_char);

    let result = 10;        // default i32
    let age:u32 = 20;
    let sum:i32 = 5-15;
    let mark:isize = 10;
    let count:usize = 30;
    println!("result value is {}", result);
    println!("sum is {} and age is {}", sum, age);
    println!("mark is {} and count is {}", mark, count);

    // u8: 0 to 255
    let age:u8 = 255;
    println!("age is {} ", age);

    let result = 10.00;        // default f64
    let interest:f32 = 8.35;
    let cost:f64 = 15000.600;  // double
    println!("result value is {}", result);
    println!("interest is {}", interest);
    println!("cost is {}", cost);
}
