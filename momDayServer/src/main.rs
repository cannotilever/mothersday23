#[macro_use] extern crate rocket;

#[get("/")]
fn index() -> String {
    String::from("Happy Mother's Day!")
}

#[launch]
fn rocket() -> _ {
    rocket::build().mount("/", routes![index])
}
