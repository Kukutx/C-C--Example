using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpTestDll
{
    public class CharpClass
    {
        private string name;
        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                name = "Your Name: " + value;
            }
        }
        public void HelloWord()
        {
            Console.WriteLine("Hello Word");
        }
        public int fnAdd(int iAdd1, int iAdd2)
        {
            return iAdd1 + iAdd2;
        }
    }
}
