using Microsoft.EntityFrameworkCore;
using server.asp.ViewModels.Timeline;

namespace server.asp.Services
{
  public class KnowledgeService : IKnowledgeService
  {
    private readonly ApplicationDbContext _dbContext;

    public KnowledgeService(ApplicationDbContext dbContext)
    {
        _dbContext = dbContext;
    } 

    public void AddKnwoledgeItem(AddKnowledgeItemModel model)
    {
      throw new System.NotImplementedException();
    }

    public TimelineModel LoadKnowledgeTimeline(int page, int pageSize)
    {
      throw new System.NotImplementedException();
    }
  }
}