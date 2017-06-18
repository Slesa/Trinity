using System;
using System.Collections.ObjectModel;
using System.Net.Http;
using System.Reactive.Linq;
using System.Threading.Tasks;
using AsyncLoad.Core;
using Newtonsoft.Json;

namespace AsyncLoad.Rx
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
			var observable = CreateModelItems();
			observable.Subscribe(item => DataModels.Add(item));
		}

		IObservable<DataModel> CreateModelItems()
		{
			var observable = Observable.Create<DataModel>(async (observer, cancel) =>
			{
				for (var i = 0; !cancel.IsCancellationRequested && i < 100; i++)
				{
				    var result = await CreateModelItemAsync(i);
				    foreach (var item in result)
				    {
				        observer.OnNext(item);
				    }
				}
			});
			return observable;
		}

		async Task<DataModel[]> CreateModelItemAsync(int id)
		{
			using (var httpClient = new HttpClient())
			{
				var url = string.Format("http://baconipsum.com/api/?type=all-meat&paras=2&start-with-lorem={0}", id);
				try
				{
					var json = await httpClient.GetStringAsync(url);
					dynamic data = JsonConvert.DeserializeObject<string[]>(json);
				    var first = data[0] as string;
				    var second = data[1] as string;
				    return new[]
				    {
				        new DataModel() {Name = string.Format("{0} - {1}", (id*2)+1, first)},
				        new DataModel() {Name = string.Format("{0} - {1}", (id*2)+2, second)},
				    };
				}
				catch (HttpRequestException ex)
				{
					System.Diagnostics.Debug.WriteLine(ex);
					throw;
				}
			}
		}
	}
}