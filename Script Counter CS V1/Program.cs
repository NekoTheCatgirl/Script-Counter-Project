Console.WriteLine("Please input the root directory of the script folder");
var path = Console.ReadLine();
if (Path.IsPathRooted(path))
{
    var csFiles = Directory.GetFiles(path, "*.cs", SearchOption.AllDirectories);
    Console.WriteLine("Found {0} script files", csFiles.Length);
    Thread.Sleep(1000);
    var start = DateTime.Now;
    ulong lines = 0;
    ulong characters = 0;
    foreach (var file in csFiles)
    {
        string[] fileContents = File.ReadAllLines(file);
        ulong fileLines = 0;
        ulong fileCharacters = 0;
        foreach (string line in fileContents)
        {
            fileLines++;
            fileCharacters += (ulong)line.Trim().Length;
        }
        Console.WriteLine("File {0} has {1} lines and {2} characters", file, fileLines, fileCharacters);
        lines += fileLines;
        characters += fileCharacters;
    }
    Console.WriteLine("Total line count {0}", lines);
    Console.WriteLine("Total character count {0}", characters);
    Console.WriteLine("Execution time total {0}s", (DateTime.Now - start).TotalSeconds);
    Console.ReadLine();
}