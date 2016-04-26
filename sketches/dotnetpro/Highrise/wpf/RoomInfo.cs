using System;

using HighRise.Model;

using Prism.Mvvm;

namespace HighRise.ViewModel
{
    public class RoomInfo : BindableBase, IRoom
    {
        private RoomState status;
        private LightState light;

        public int Id { get; }

        public string Name { get; }

        public RoomState Status
        {
            get
            {
                return status;
            }

            set
            {
                if (value != status)
                {
                    status = value;
                    OnPropertyChanged(() => Status);
                }
            }
        }

        public LightState Light
        {
            get
            {
                return light;
            }

            set
            {
                if (value != light)
                {
                    light = value;
                    OnPropertyChanged(() => Light);
                }
            }
        }

        public RoomInfo(IRoom room)
        {
            if (room == null)
            {
                throw new ArgumentNullException(nameof(room));
            }

            Id = room.Id;
            Name = room.Name;
            Status = room.Status;
            Light = room.Light;
        }
    }
}
