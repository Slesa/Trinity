using System;
using System.Collections.ObjectModel;
using System.Diagnostics.CodeAnalysis;

namespace HighRise.Model
{
    [ExcludeFromCodeCoverage]
    public class BuildingRepositoryMock : IBuildingRepository
    {
        private const int BuildingId = 42;
        private const string BuildingName = "Science Park 2";
        private const int LevelCount = 11;

        private const int RoomCountOnEachFloor = 2;

        private const int LevelIdCreationMultiplicator = 100;

        private readonly Random random = new Random((int)DateTime.Now.Ticks);

        private const int errorStateProbability = 4;

        private const string RoomNameBase = "Room ";
        private const string RoomIdFloorSeparator = "-";

        private ReadOnlyObservableCollection<IRoom> CreateRooms(int roomCount, int level)
        {
            var rooms = new ObservableCollection<IRoom>();
            for (int i = 1; i <= roomCount; i++)
            {
                string roomName = CreateRoomName(i, level);
                int roomId = CreateRoomId(i, level);
                RoomState roomState = GetRandomRoomState();
                var room = new Room(roomId, roomName);
                room.Status = roomState;
                rooms.Add(room);
            }

            return new ReadOnlyObservableCollection<IRoom>(rooms);
        }

        private int CreateRoomId(int roomIdOnLevel, int level)
        {
            int levelId = level * LevelIdCreationMultiplicator;
            return levelId + roomIdOnLevel;
        }

        private string CreateRoomName(int roomIdOnLevel, int level)
        {
            return string.Concat(RoomNameBase, level, RoomIdFloorSeparator, roomIdOnLevel);
        }

        private RoomState GetRandomRoomState()
        {
            RoomState state = RoomState.Ok;
            bool useErrorState = random.Next(0, errorStateProbability) % errorStateProbability == 0;
            if (useErrorState)
            {
                state = RoomState.Error;
            }

            return state;
        }

        private ReadOnlyObservableCollection<IFloor> CreateFloors(int levelCount)
        {
            var floors = new ObservableCollection<IFloor>();
            for (int i = 1; i <= levelCount; i++)
            {
                ReadOnlyObservableCollection<IRoom> rooms = CreateRooms(RoomCountOnEachFloor, i);
                floors.Insert(0, new Floor(i, rooms));
            }

            return new ReadOnlyObservableCollection<IFloor>(floors);
        }

        public IBuilding GetBuilding()
        {
            ReadOnlyObservableCollection<IFloor> floors = CreateFloors(LevelCount);
            return new Building(BuildingId, BuildingName, floors);
        }
    }
}
