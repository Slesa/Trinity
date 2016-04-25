using System;

namespace HighRise.Model
{
    public class Room : IRoom
    {
        public int Id { get; }

        public string Name { get; }

        public RoomState Status { get; set; }

        public LightState Light { get; set; }

        public Room(int id, string name)
        {
            if (name == null)
            {
                throw new ArgumentNullException(nameof(name));
            }

            if (string.IsNullOrEmpty(name))
            {
                throw new ArgumentException(nameof(name));
            }

            Id = id;
            Name = name;
            Status = RoomState.Ok;
            Light = LightState.Off;
        }
    }
}
