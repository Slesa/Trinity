using System.Collections.Generic;

namespace server.asp.ViewModels.Timeline
{
    public class AddKnowledgeItemModel
    {
        public string Content { get; set; }
        public LinkModel Link { get; set; }
        public IEnumerable<DocumentModel> Documents { get; set; }
    }
}