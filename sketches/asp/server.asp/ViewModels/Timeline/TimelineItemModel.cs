using System;
using System.Collections.Generic;

namespace server.asp.ViewModels.Timeline
{
    public class TimelineItemModel
    {
        public int Id { get; set; }
        public string Content { get; set; }
        public string User { get; set; }
        public DateTime Date { get; set; }
        public LinkModel Link { get; set; }
        public IEnumerable<DocumentModel> Documents { get; set; }
    }
}