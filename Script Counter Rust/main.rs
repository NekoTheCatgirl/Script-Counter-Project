use std::io::{stdin, BufRead, BufReader};
use std::fs::File;
use walkdir::{DirEntry, WalkDir};

fn is_rust(entry: &DirEntry) -> bool
{
    return entry.file_name()
    .to_str()
    .map(|s: &str| s.ends_with(".rs"))
    .unwrap_or(false);
}

fn get_files(path: String) -> Vec<String>
{
    let mut files: Vec<String> = vec![];
    let index: usize = 0;
    let walker = WalkDir::new(path).into_iter();
    for entry in walker.filter_entry(|e| is_rust(e)) {
        let entry = entry.unwrap();
        files.insert(index, entry.path().as_os_str().to_str().unwrap().to_string());
    }
    return files;
}

struct FileInfo {
    lines: u64,
    characters: u64,
}

fn read_file(path: String) -> FileInfo
{
    let mut lines: u64 = 0;
    let mut characters: u64 = 0;
     
    let file = BufReader::new(File::open(path).expect("Unable to open file"));

    for line in file.lines()
    {
        let line = line.unwrap();
        lines += 1;
        characters += line.len() as u64;
    }

    return FileInfo
    {
        lines: lines,
        characters: characters 
    }
}

fn main() 
{
    println!("Please input the root directory of the script folder");
    let mut path: String = String::new();
    stdin().read_line(&mut path).unwrap();
    let files: Vec<String> = get_files(path);
    let mut lines: u64 = 0;
    let mut characters: u64 = 0;
    for file in files{
        let info: FileInfo = read_file(file);
        lines += info.lines;
        characters += info.characters;
    }
    println!("Total line count {}", lines);
    println!("Total character count {}", characters);
}
