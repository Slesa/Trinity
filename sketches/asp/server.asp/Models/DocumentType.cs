using System;

namespace server.asp.Models
{
    [Flags]
    public enum DocumentType
    {
        Audio,
        Video,
        Image,
        Document
    }
}