namespace AkkaTalk.Models
{
    public class Message
    {
        private readonly string _msg;

        public Message(string msg)
        {
            _msg = msg;
        }

        public string Text { get { return _msg; } }
    }
}