using System.Collections.Concurrent;
using ScriptCounterV3;

var options = Options.Get();

Console.WriteLine("Please input the root directory of the script folder");
var path = Console.ReadLine();
if (Path.IsPathRooted(path))
{
    options = Options.Get();

    var files = new List<string>();
    foreach (var type in options.FileTypes)
    {
        files.AddRange(Directory.GetFiles(path, type, SearchOption.AllDirectories));
    }

    var filteredFiles = new List<string>();
    files.ForEach(f => { if (options.PathFilters.Any(x => f.Contains(x)) is false) filteredFiles.Add(f); });
    
    Console.WriteLine("Found {0} script files", filteredFiles.Count);
    Thread.Sleep(1000);
    var start = DateTime.Now;

    ConcurrentBag<ulong> linesInstances = new();
    ConcurrentBag<ulong> charactersInstances = new();

    Parallel.ForEach(filteredFiles, file =>
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
        linesInstances.Add(fileLines);
        charactersInstances.Add(fileCharacters);
    });

    ulong lines = 0;
    ulong characters = 0;

    var lineList = linesInstances.ToArray();
    var charactersList = charactersInstances.ToArray();

    for (int i = 0; i < charactersInstances.Count; i++)
    {
        lines += lineList[i];
        characters += charactersList[i];
    }

    Console.WriteLine("Total line count {0}", lines);
    Console.WriteLine("Total character count {0}", characters);
    Console.WriteLine("Execution time total {0}s", (DateTime.Now - start).TotalSeconds);
    Console.ReadLine();
}