using System.Threading.Tasks;
using server.asp.ViewModels.Timeline;

namespace server.asp.Services
{
    public interface IKnowledgeService
    {
         TimelineModel LoadKnowledgeTimeline(int page, int pageSize);
         void AddKnwoledgeItem(AddKnowledgeItemModel model);
    }
}