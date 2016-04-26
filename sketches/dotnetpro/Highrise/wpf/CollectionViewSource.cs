using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Globalization;
using System.Linq;

namespace HighRise.ViewModel
{
    public class CollectionViewSource<T> : ICollectionView<T>
    {
        private readonly ICollectionView collectionView;

        public CollectionViewSource(ICollectionView generic)
        {
            collectionView = generic;
        }

        private class CollectionViewEnumerator : IEnumerator<T>
        {
            private readonly IEnumerator enumerator;
            public CollectionViewEnumerator(IEnumerator theEnumerator)
            {
                enumerator = theEnumerator;
            }

            public void Dispose()
            {
            }

            public bool MoveNext()
            {
                return enumerator.MoveNext();
            }

            public void Reset()
            {
                enumerator.Reset();
            }

            public T Current => (T)enumerator.Current;

            object IEnumerator.Current => Current;
        }

        public IEnumerator<T> GetEnumerator()
        {
            return new CollectionViewEnumerator(collectionView.GetEnumerator());
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return collectionView.GetEnumerator();
        }

        public bool Contains(object item)
        {
            return collectionView.Contains(item);
        }

        public void Refresh()
        {
            collectionView.Refresh();
        }

        public IDisposable DeferRefresh()
        {
            return collectionView.DeferRefresh();
        }

        public bool MoveCurrentToFirst()
        {
            return collectionView.MoveCurrentToFirst();
        }

        public bool MoveCurrentToLast()
        {
            return collectionView.MoveCurrentToLast();
        }

        public bool MoveCurrentToNext()
        {
            return collectionView.MoveCurrentToNext();
        }

        public bool MoveCurrentToPrevious()
        {
            return collectionView.MoveCurrentToPrevious();
        }

        public bool MoveCurrentTo(object item)
        {
            return collectionView.MoveCurrentTo(item);
        }

        public bool MoveCurrentToPosition(int position)
        {
            return collectionView.MoveCurrentToPosition(position);
        }

        public CultureInfo Culture
        {
            get { return collectionView.Culture; }
            set { collectionView.Culture = value; }
        }

        public IEnumerable SourceCollection => collectionView.SourceCollection;

        public Predicate<object> Filter
        {
            get { return collectionView.Filter; }
            set { collectionView.Filter = value; }
        }

        public bool CanFilter => collectionView.CanFilter;

        public SortDescriptionCollection SortDescriptions => collectionView.SortDescriptions;

        public bool CanSort => collectionView.CanSort;

        public bool CanGroup => collectionView.CanGroup;

        public ObservableCollection<GroupDescription> GroupDescriptions => collectionView.GroupDescriptions;

        public ReadOnlyObservableCollection<object> Groups => collectionView.Groups;

        public bool IsEmpty => collectionView.IsEmpty;

        public object CurrentItem => collectionView.CurrentItem;

        public int CurrentPosition => collectionView.CurrentPosition;

        public bool IsCurrentAfterLast => collectionView.IsCurrentAfterLast;

        public bool IsCurrentBeforeFirst => collectionView.IsCurrentBeforeFirst;

        public event CurrentChangingEventHandler CurrentChanging
        {
            add
            {
                lock (objectLock)
                {
                    collectionView.CurrentChanging += value;
                }
            }
            remove
            {
                lock (objectLock)
                {
                    collectionView.CurrentChanging -= value;
                }
            }
        }

        readonly object objectLock = new object();

        public event EventHandler CurrentChanged
        {
            add
            {
                lock (objectLock)
                {
                    collectionView.CurrentChanged += value;
                }
            }
            remove
            {
                lock (objectLock)
                {
                    collectionView.CurrentChanged -= value;
                }
            }
        }

        public event NotifyCollectionChangedEventHandler CollectionChanged
        {
            add
            {
                lock (objectLock)
                {
                    collectionView.CollectionChanged += value;
                }
            }
            remove
            {
                lock (objectLock)
                {
                    collectionView.CollectionChanged -= value;
                }
            }
        }

        public IEnumerable<T> SourceCollectionGeneric => collectionView.Cast<T>();
    }
}
