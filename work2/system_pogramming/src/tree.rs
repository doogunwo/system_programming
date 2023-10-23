use std::collections::BTreeMap;
use std::io;

//struct record

struct Record{
    name : String,
    mid_term_score : i32,
    final_score : i32,
}

pub fn tree(){
    let mut recordMap = BTreeMap::new();
    let mut num = String::new();

    println!("Enter number of record(num):");

    io::stdin()
        .read_line(&mut num)
        .expect("Failed to read line");
    
    let mut num = num.trim().parse()
        .expect("Invalid input");
    
    for _ in 0..num{
        let mut name = String::new();
        let mut mid_term_score = String::new();
        let mut final_score = String::new();

        println!("Enter student name:");
        io::stdin()
            .read_line(&mut name)
            .expect("Failed to read line");
        let name = name.trim().to_string();

        println!("Enter midterm score:");
        io::stdin()
            .read_line(&mut mid_term_score)
            .expect("Failed to read line");
        let mid_term_score:i32 = mid_term_score.trim().parse()
            .expect("Failed to read line");
        
        println!("Enter final score:");
        io::stdin()
            .read_line(&mut final_score)
            .expect("Failed to read line");
        let final_score:i32 = final_score.trim().parse()
            .expect("Failed to read line");
        
        let data = Record {
                name: name.clone(),
                mid_term_score,
                final_score,
            };
        
        recordMap.insert(name, data);
    }

    println!("Enter the name of a student to search:");
    let mut search_name = String::new();

    io::stdin()
        .read_line(&mut search_name)
        .expect("Failed to read line");

    search_name = search_name.trim().to_string();
    
    match recordMap.get(&search_name){
        Some(Record) =>{
            print!("Name: {} ",Record.name);
            print!("Mid score: {} ",Record.mid_term_score);
            print!("Final score: {} ",Record.final_score);
        }
        None => {
            print!("not found");
        }
    }
}
