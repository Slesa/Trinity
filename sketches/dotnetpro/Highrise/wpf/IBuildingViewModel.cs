using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Input;

using HighRise.Model;

namespace HighRise.ViewModel
{
    public interface IBuildingViewModel : INotifyPropertyChanged
    {
        IBuilding Building { get; }

        string FilterText { get; set; }

        ICommand ResetFilterCommand { get; }

        IEnumerable<IRoom> Rooms { get; }

        IRoom SelectedRoom { get; set; }

        ICommand ToggleLightCommand { get; }
    }
}
