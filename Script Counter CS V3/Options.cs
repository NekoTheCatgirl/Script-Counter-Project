#nullable disable
using Newtonsoft.Json;

namespace ScriptCounterV3
{
    public class Options
    {
        public const string FilePath = "Options.json";

        public List<string> FileTypes = new();
        public List<string> PathFilters = new();

        public static Options Get()
        {
            if (File.Exists(FilePath))
            {
                return JsonConvert.DeserializeObject<Options>(File.ReadAllText(FilePath));
            }
            var options = new Options();
            options.FileTypes.Add("*.cs");
            File.WriteAllText(FilePath, JsonConvert.SerializeObject(options));
            return options;
        }
    }
}
