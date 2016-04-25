using System;
using System.Collections.ObjectModel;
using System.Linq;

namespace HighRise.Model
{
    public class Building : IBuilding
    {
        public int Id { get; }

        public string Name { get; }

        public ReadOnlyObservableCollection<IFloor> Floors { get; }

        public ReadOnlyObservableCollection<IRoom> Rooms { get; private set; }

        public Building(int id, string name, ReadOnlyObservableCollection<IFloor> floors)
        {
            if (name == null)
            {
                throw new ArgumentNullException(nameof(name));
            }

            if (string.IsNullOrEmpty(name))
            {
                throw new ArgumentException(nameof(name));
            }

            if (floors == null)
            {
                throw new ArgumentNullException(nameof(floors));
            }

            if (!floors.Any())
            {
                throw new ArgumentException(@"A building must have at least one floor.", nameof(floors));
            }

            Id = id;
            Name = name;
            Floors = floors;
            LoadRooms();
        }

        private void LoadRooms()
        {
            var rooms = new ObservableCollection<IRoom>();
            foreach (var floor in Floors)
            {
                if (!floor.Rooms.Any())
                {
                    throw new ArgumentException(@"A floor must have at least one room.", nameof(floor.Rooms));
                }

                foreach (var room in floor.Rooms)
                {
                    rooms.Add(room);
                }
            }

            Rooms = new ReadOnlyObservableCollection<IRoom>(rooms);
        }
    }
}
