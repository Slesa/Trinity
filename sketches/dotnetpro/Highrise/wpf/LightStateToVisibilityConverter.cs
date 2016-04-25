using System;
using System.Globalization;
using System.Windows;
using System.Windows.Data;

using HighRise.Model;

namespace HighRise.Glue
{
    public class LightStateToVisibilityConverter : IValueConverter
    {
        /// <summary>
        /// Converts a <see cref="LightState"/> enum value into a <see cref="Visibility"/>
        /// </summary>
        /// <param name="value">Value of the conversion.</param>
        /// <param name="targetType">TargetType is not used.</param>
        /// <param name="parameter">Parameter is not used.</param>
        /// <param name="culture">Culture is not used.</param>
        /// <returns>The conversion result.</returns>
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value == null)
            {
                throw new ArgumentNullException("value");
            }

            if (!(value is LightState))
            {
                throw new ArgumentException($"value must be type of '{typeof(LightState)}'");
            }

            var lightState = (LightState)value;

            var returnValue = Visibility.Collapsed;
            if (lightState == LightState.On)
            {
                returnValue = Visibility.Visible;
            }

            return returnValue;
        }

        /// <summary>
        /// Converts a <see cref="Visibility"/> value back to a <see cref="LightState"/> value.
        /// </summary>
        /// <param name="value">Value of the back conversion.</param>
        /// <param name="targetType">TargetType is not used.</param>
        /// <param name="parameter">Parameter is not used.</param>
        /// <param name="culture">Culture is not used.</param>
        /// <returns>The back conversion result.</returns>
        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value == null)
            {
                throw new ArgumentNullException("value");
            }

            if (!(value is Visibility))
            {
                throw new ArgumentException($"value must be type of '{typeof(Visibility)}'");
            }

            LightState returnValue;
            if (value.Equals(Visibility.Visible))
            {
                returnValue = LightState.On;
            }
            else if (value.Equals(Visibility.Collapsed))
            {
                returnValue = LightState.Off;
            }
            else
            {
                throw new NotSupportedException("This Visibility is not supported by this converter.");
            }

            return returnValue;
        }
    }
}
