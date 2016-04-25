using System.Collections.ObjectModel;

namespace HighRise.Model
{
    public interface IBuilding
    {
        int Id { get; }

        string Name { get; }

        ReadOnlyObservableCollection<IFloor> Floors { get; }

        ReadOnlyObservableCollection<IRoom> Rooms { get; }
    }
}