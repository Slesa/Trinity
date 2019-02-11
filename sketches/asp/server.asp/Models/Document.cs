namespace server.asp.Models
{
    public class Document
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public DocumentType Type { get; set; }
        public string Source { get; set; }
        public KnowledgeEntry KnowledgeEntry { get; set; }
        public int KnowledgeEntryId { get; set; }
    }
}