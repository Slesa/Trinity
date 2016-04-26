using System.Collections.Generic;
using System.ComponentModel;

namespace HighRise.ViewModel
{
    public interface ICollectionView<T> : IEnumerable<T>, ICollectionView
    {
        IEnumerable<T> SourceCollectionGeneric { get; }
    }
}
