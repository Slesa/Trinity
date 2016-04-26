using System;
using System.Collections.ObjectModel;

using HighRise.Model;

using Prism.Mvvm;

namespace HighRise.ViewModel
{
    public class BuildingInfo : BindableBase, IBuilding
    {
        public int Id { get; }

        public string Name { get; }

        public ReadOnlyObservableCollection<IFloor> Floors { get; }

        public ReadOnlyObservableCollection<IRoom> Rooms { get; }

        public BuildingInfo(IBuilding building)
        {
            if (building == null)
            {
                throw new ArgumentNullException(nameof(building));
            }

            Id = building.Id;
            Name = building.Name;
            Floors = InfoObjectFactory.CreateFloorInfos(building.Floors);
            Rooms = InfoObjectFactory.GetRoomInfos(Floors);
        }
    }
}
