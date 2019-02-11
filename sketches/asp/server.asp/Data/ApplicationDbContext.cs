using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using server.asp.Models;
namespace server.asp.Data
{
    public class ApplicationDbContext : IdentityDbContext<ApplicationUser>
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
        : base(options)
        {
        }       

        public DbSet<KnowledgeEntry> KnowledgeEntries { get; set; }
        public DbSet<Link> Links { get; set; }
        public DbSet<Document> Documents { get; set; }
    }
}