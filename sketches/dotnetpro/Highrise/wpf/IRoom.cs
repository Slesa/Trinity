namespace HighRise.Model
{
    public interface IRoom
    {
        int Id { get; }

        string Name { get; }

        RoomState Status { get; set; }

        LightState Light { get; set; }
    }
}