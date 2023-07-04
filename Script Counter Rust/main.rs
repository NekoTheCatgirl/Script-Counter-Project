use std::io::{stdin, BufRead, BufReader};
use std::{fs, vec};
use std::fs::File;

fn walk_directory(path: &str, file_paths: &mut Vec<String>, extension: &str) {
    if let Ok(entries) = fs::read_dir(path) {
        for entry in entries {
            if let Ok(entry) = entry {
                let entry_path = entry.path();
                if entry_path.is_dir() {
                    walk_directory(entry_path.to_str().unwrap(), file_paths, extension);
                } else if let Some(file_extension) = entry_path.extension().and_then(|ext| ext.to_str()) {
                    if file_extension.eq_ignore_ascii_case(extension) {
                        if let Some(file_path) = entry_path.to_str() {
                            file_paths.push(file_path.to_string());
                        }
                    }
                }
            }
        }
    }
}

fn get_files(path: String) -> Vec<String>
{
    let mut files: Vec<String> = vec![];
    walk_directory(path.as_str(), &mut files, ".rs");
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
     
    let file: BufReader<File> = BufReader::new(File::open(path).expect("Unable to open file"));

    for line in file.lines()
    {
        let line: String = line.unwrap();
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
    let sanitized_path: String = path.trim_end().to_string();
    let files: Vec<String> = get_files(sanitized_path);
    println!("Found {} files", files.len());
    let mut lines: u64 = 0;
    let mut characters: u64 = 0;
    for file in files{
        let info: FileInfo = read_file(file);
        lines += info.lines;
        characters += info.characters;
    }
    println!("Total line count {}", lines);
    println!("Total character count {}", characters);
    let mut input = String::new();
    stdin().read_line(&mut input).expect("Failed to read line");
}
