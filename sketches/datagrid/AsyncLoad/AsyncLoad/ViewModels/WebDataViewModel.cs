/*
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using AsyncLoad.Core;

namespace AsyncLoad
{
    public class WebDataViewModel
    {
        public WebDataViewModel()
        {
            DataModels = new ObservableCollection<DataModel>();
            CreateModel();
        }

        public ObservableCollection<DataModel> DataModels { get; private set; }

        void CreateModel()
        {
            //IEnumerable<DataModel> result;
            //Task.Factory.StartNew(() =>
            //{
            var tasks = CreateModelItems();

            //var enumerable = items.Select(async t => await t);
            foreach (var task in tasks)
            {
                //await task;
                DataModels.Add(task.Result);
            }
        }

        IEnumerable<Task<DataModel>> CreateModelItems()
        {
            for (var i = 1; i < 100; i++)
            {
                Thread.Sleep(100);
                yield return Task.Factory.StartNew(() => new DataModel() {Name = string.Format("Model {0}", i)});
            }
        }
    }
}
*/