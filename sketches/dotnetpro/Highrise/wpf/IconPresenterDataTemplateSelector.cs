using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace HighRise.Interactivity
{
    /// <summary>
    /// A <see cref="DataTemplateSelector"/> which selects a template depending on whehter
    /// an <see cref="ImageSource"/> or a <see cref="StreamGeometry"/> is given.
    /// An <see cref="ImageSource"/> is a rasterized png image.
    /// A <see cref="StreamGeometry"/> is a vector image as path.
    /// </summary>
    public class IconPresenterDataTemplateSelector : DataTemplateSelector
    {
        public DataTemplate StreamGeometryTemplate { get; set; }

        public DataTemplate ImageSourceTemplate { get; set; }

        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            DataTemplate dataTemplate = null;
            if (item != null)
            {
                Type t = item.GetType();
                dataTemplate = SelectTemplate(t, item);
            }

            return dataTemplate;
        }

        protected virtual DataTemplate SelectTemplate(Type itemType, object item)
        {
            if (itemType == null)
            {
                throw new ArgumentNullException(nameof(itemType));
            }

            if (item == null)
            {
                throw new ArgumentNullException(nameof(item));
            }

            DataTemplate dataTemplate = null;
            if (itemType == typeof(StreamGeometry))
            {
                if (StreamGeometryTemplate == null)
                {
                    throw new InvalidOperationException(
                        $"No value set for property {nameof(StreamGeometryTemplate)}({itemType.FullName}).");
                }

                dataTemplate = StreamGeometryTemplate;
            }
            else if (typeof(ImageSource).IsAssignableFrom(itemType))
            {
                if (ImageSourceTemplate == null)
                {
                    throw new InvalidOperationException(
                        $"No value set for property {nameof(ImageSourceTemplate)}({itemType.FullName}).");
                }

                dataTemplate = ImageSourceTemplate;
            }

            return dataTemplate;
        }
    }

}
