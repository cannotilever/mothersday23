#[macro_use] extern crate rocket;
use rocket::State;
use std::sync::atomic::{AtomicUsize, Ordering};

#[get("/")]
fn index() -> String {
    String::from("Happy Mother's Day!")
}

#[get("/tag/<id>")]
fn tagHandler(id: &str, counter: &State<AtomicUsize>) -> String {
    let mut retn: String = String::from("Invalid code!");
    let mut toAdd: usize = 0;
    match id {
        "love" => {
            retn = "No one really knows just what I am, neither do I most days. It's okay though, I'm just happy to hang out here.".to_string();
            toAdd = 1; }
        "you" => {
            retn = "Is golf too interesting for you? There's no need to feel blue, I think we'll hit it off just fine and have a smashing time!".to_string();
            toAdd = 2; }
        "forever" => {
            retn = "I have a striking similarity to locks and laptops though I am neither. I am also the oldest electronic device in the house.".to_string();
            toAdd = 3; }
        "mom" => {
            retn = "You win!".to_string();
            toAdd = 5; }

        "piano" => toAdd = 4,
            
        _ => toAdd = 0,
    }
    if toAdd != 0 {
        counter.store(toAdd, Ordering::Relaxed);
        }
    retn
}

#[get("/status")]
fn showStatus(counter: &State<AtomicUsize>) -> String{
    format!("{}",counter.load(Ordering::Relaxed))
}

#[launch]
fn rocket() -> _ {
    rocket::build().mount("/", routes![index, tagHandler, showStatus]).manage( AtomicUsize::new(0))
}
