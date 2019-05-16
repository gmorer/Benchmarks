extern crate serde_derive;
extern crate reqwest;
extern crate regex;

use regex::Regex;
use std::env;

const USAGE: &str = "Usage: ./test_rs [URI] [REGEX]";

fn main() -> Result<(), Box<std::error::Error>> {
    let args: Vec<String> = env::args().collect();
    if args.len() < 3 {
        eprintln!("{}", USAGE);
        return Err(Box::new(core::fmt::Error {}));
    }
    let mut resp = reqwest::get(&args[1])?;
    let body = resp.text()?;
    let headers = resp.headers();
    let find_token = Regex::new(&args[2])?;
    let token = find_token.captures(&body).expect("no matches").get(1).expect("invalid match").as_str();
    println!("{}", token);
    Ok(())
}
