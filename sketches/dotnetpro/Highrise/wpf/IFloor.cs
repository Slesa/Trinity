using System.Collections.ObjectModel;

namespace HighRise.Model
{
    public interface IFloor
    {
        int Id { get; }

        ReadOnlyObservableCollection<IRoom> Rooms { get; }
    }
}