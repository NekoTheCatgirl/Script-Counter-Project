import java.io.File;
import java.io.FileNotFoundException;
import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;

public class Program 
{
	public static void main(String[] args)
	{
		System.out.println("Please input the root directory of the script folder");
		Scanner input = new Scanner(System.in);
		String targetDir = input.nextLine();
		input.close();
		
		File file = new File(targetDir);
		if (file.isAbsolute())
		{
			List<String> files = new ArrayList<String>();
			ScanDir(targetDir, files);
			
			long lines = 0;
			long characters = 0;
			
			for (String f : files)
			{
				FileInfo fi = GetFileInfo(f);
				lines += fi.Lines;
				characters += fi.Characters;
			}
			
			System.out.println(String.format("Total line count %d", lines));
			System.out.println(String.format("Total character count %d", characters));
		}
	}
	
	public static FileInfo GetFileInfo(String file)
	{
		try
		{
			File f = new File(file);
			Scanner reader = new Scanner(f);
			
			long lines = 0;
			long characters = 0;
			
			while (reader.hasNextLine())
			{
				lines++;
				String l = reader.nextLine();
				characters += l.length();
			}
			System.out.println(String.format("File %s has %d lines and %d characters", file, lines, characters));
			
			reader.close();
			
			return new FileInfo(lines, characters);
		}
		catch (FileNotFoundException e)
		{
			System.out.println(String.format("Could not open %s", file));
			return new FileInfo(0, 0);
		}
	}
	
	public static void ScanDir(String dir, List<String> files) 
	{
		File directory = new File(dir);
		File[] fList = directory.listFiles();
		
		if (fList != null)
		{
			for (File file : fList)
			{
				if (file.isFile())
				{
					if (file.getAbsolutePath().endsWith(".java")) 
					{
						files.add(file.getAbsolutePath());
					}
				}
				else
				{
					ScanDir(file.getAbsolutePath(), files);
				}
			}
		}
	}
}