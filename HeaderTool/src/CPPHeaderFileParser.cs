using HeaderTool.src;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace HeaderTool
{
    public enum AttributeType  {Class, Property }
    public struct Attributes
    {
        public AttributeType attributeType;
        public string type;
        public string name;
        public string defualtValue;
        public bool hasValue;
    }

    public class CPPHeaderFileParser
    {
        public CPPHeaderFileParser()
        {
            
        }

        public void Parse(List<Module> modules)
        {
            foreach(Module module in modules)
            {
                foreach(string path in module.GetModules())
                {
                    if (!Directory.Exists(path)) break;

                    string[] files = Directory.GetFiles(path);

                    foreach (string file in files)
                    {
                        if (CheckFile(file))
                        {
                            Attributes[] attribues = ParseFileContents(file);
                        }
                    }
                }
            }
        }

        private bool CheckFile(string file)
        {
            return ExtChecker.IsValidExtension(file);
        }

        private Attributes[] ParseFileContents(string file)
        {
            Attributes[] attributes = { };
            string[] lines = System.IO.File.ReadAllLines(file);
            for (int i = 0; i < lines.Length; i++)
            {
                string line = lines[i];
                

                if (line == "CLASS()")
                {
                    string nextline = lines[i + 1];
                    Attributes attribute = new Attributes();
                    attribute.attributeType = AttributeType.Class;
                    string[] property = nextline.Split(' ');
                    if (property.Length == 2)
                    {
                        attribute.type = property[0];
                        attribute.name = property[1];
                        attribute.defualtValue = "";
                        attribute.hasValue = false;
                    }
                    else if (property.Length == 4)
                    {

                        attribute.type = property[0];
                        attribute.name = property[1];
                        attribute.defualtValue = property[2];
                        attribute.hasValue = false;

                    }
                    attributes.Append(attribute);
                }

                if (line == "PROPERTY()" || line == "\tPROPERTY()")
                {
                    string nextline = lines[i + 1];
                    Attributes attribute = new Attributes();
                    attribute.attributeType = AttributeType.Property;

                    string[] property = nextline.Split(' ');
                    if(property.Length == 2)
                    {
                        
                        attribute.type = property[0];
                        attribute.name = property[1];
                        attribute.defualtValue = "";
                        attribute.hasValue = false;
                    }
                    else if(property.Length == 4)
                    {

                        attribute.type = property[0];
                        attribute.name = property[1];
                        attribute.defualtValue = property[3];
                        attribute.hasValue = true;
                        
                    }
                    attributes.Append(attribute);
                }
            }
            return attributes ;
        }

        private void GenerateFile(string file, Attributes[] attribues)
        {

        }

        private CheckExtension ExtChecker = new CheckExtension();
    }
}