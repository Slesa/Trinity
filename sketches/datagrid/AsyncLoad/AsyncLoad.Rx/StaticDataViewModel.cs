using System;
using System.Collections.ObjectModel;
using System.Reactive.Linq;
using System.Threading.Tasks;
using AsyncLoad.Core;

namespace AsyncLoad.Rx
{
    public class StaticDataViewModel
    {
        public StaticDataViewModel()
        {
            DataModels = new ObservableCollection<DataModel>();
            CreateModel();
        }

        public ObservableCollection<DataModel> DataModels { get; private set; }

        void CreateModel()
        {
            var observable = CreateModelItems();
			observable.Subscribe(item => DataModels.Add(item));
        }


        IObservable<DataModel> CreateModelItems()
        {
	        var observable = Observable.Create<DataModel>(async (observer, cancel) =>
	        {
		        for (var i = 1; !cancel.IsCancellationRequested && i < 100; i++)
		        {
			        observer.OnNext(await CreateModelItemAsync(i));
		        }
	        });
	        return observable;
        }

	    async Task<DataModel> CreateModelItemAsync(int id)
	    {
			await Task.Delay(100);
			return new DataModel() { Name = string.Format("Model {0}", id) };
		}

	}
}