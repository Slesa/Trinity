using System;
using System.Collections.ObjectModel;
using System.Linq;

namespace HighRise.Model
{
    public class Floor : IFloor
    {
        public int Id { get; }

        public ReadOnlyObservableCollection<IRoom> Rooms { get; }

        public Floor(int id, ReadOnlyObservableCollection<IRoom> rooms)
        {
            if (rooms == null)
            {
                throw new ArgumentNullException(nameof(rooms));
            }

            if (!rooms.Any())
            {
                throw new ArgumentException(@"A floor must have at least one room.", nameof(rooms));
            }

            Id = id;
            Rooms = rooms;
        } 
    }
}
