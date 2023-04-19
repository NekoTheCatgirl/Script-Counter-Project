import os

def getFiles(path: str) -> list:
    files = []
    
    for (dir_path, dir_names, file_names) in os.walk(path):
        for i in file_names:
            if i.endswith(".cs"):
                files.append(os.path.join(dir_path, i))
    
    return files

print("Please input the rood directory of the script folder")
path = input(">")
if (os.path.isabs(path)):
    pyFiles = getFiles(path)

    print(f"Found {len(pyFiles)} script files")

    lines = 0
    characters = 0

    for file in pyFiles:
        with open(file, 'r') as f:
            for line in f:
                lines += 1

                characters += len(line)
    
    print(f"Total line count {lines}")
    print(f"Total character count {characters}")
    input()