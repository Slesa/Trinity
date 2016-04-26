using System;
using System.Collections.ObjectModel;

using HighRise.Model;

using Prism.Mvvm;

namespace HighRise.ViewModel
{
    public class FloorInfo : BindableBase, IFloor
    {
        public int Id { get; }

        public ReadOnlyObservableCollection<IRoom> Rooms { get; }

        public FloorInfo(IFloor floor)
        {
            if (floor == null)
            {
                throw new ArgumentNullException(nameof(floor));
            }

            Id = floor.Id;
            Rooms = InfoObjectFactory.CreateRoomInfos(floor.Rooms);
        }

    }
}
