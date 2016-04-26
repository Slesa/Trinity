using System.Collections.Generic;
using System.Collections.ObjectModel;

using HighRise.Model;

namespace HighRise.ViewModel
{
    public class InfoObjectFactory
    {
        public static BuildingInfo CreateBuildingInfoFor(IBuilding building)
        {
            return new BuildingInfo(building);
        }

        public static ReadOnlyObservableCollection<IFloor> CreateFloorInfos(IEnumerable<IFloor> floors)
        {
            var floorInfos = new ObservableCollection<IFloor>();
            foreach (var floor in floors)
            {
                floorInfos.Add(CreateFloorInfo(floor));
            }

            return new ReadOnlyObservableCollection<IFloor>(floorInfos);
        }

        public static FloorInfo CreateFloorInfo(IFloor floor)
        {
            return new FloorInfo(floor);
        }

        public static RoomInfo CreateRoomInfo(IRoom room)
        {
            return new RoomInfo(room);
        }

        public static ReadOnlyObservableCollection<IRoom> GetRoomInfos(ReadOnlyObservableCollection<IFloor> floorInfos)
        {
            var roomInfos = new ObservableCollection<IRoom>();
            foreach (var floorInfo in floorInfos)
            {
                foreach (var room in floorInfo.Rooms)
                {
                    if (room is RoomInfo)
                    {
                        roomInfos.Add(room);
                    }
                    else
                    {
                        roomInfos.Add(new RoomInfo(room));
                    }
                }
            }

            return new ReadOnlyObservableCollection<IRoom>(roomInfos);
        }

        public static ReadOnlyObservableCollection<IRoom> CreateRoomInfos(IEnumerable<IRoom> rooms)
        {
            var roomInfos = new ObservableCollection<IRoom>();
            foreach (var room in rooms)
            {
                roomInfos.Add(new RoomInfo(room));
            }

            return new ReadOnlyObservableCollection<IRoom>(roomInfos);
        }
    }
}
