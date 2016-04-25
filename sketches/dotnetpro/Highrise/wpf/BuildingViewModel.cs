using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Input;

using HighRise.Model;

using Prism.Commands;
using Prism.Mvvm;

namespace HighRise.ViewModel
{
    public class BuildingViewModel : BindableBase, IBuildingViewModel
    {
        private string filterText;
        private IRoom selectedRoom;
        private readonly DelegateCommand resetFilterCommand;
        private readonly DelegateCommand toggleLightCommand;
        private readonly ICollectionView<IRoom> filteredRooms;

        public string FilterText
        {
            get
            {
                return filterText;
            }

            set
            {
                if (value != filterText)
                {
                    filterText = value;
                    OnPropertyChanged(() => FilterText);
                    resetFilterCommand.RaiseCanExecuteChanged();
                    filteredRooms.Refresh();
                }
            }
        }

        public ICommand ResetFilterCommand => resetFilterCommand;

        public ICommand ToggleLightCommand => toggleLightCommand;

        public IBuilding Building { get; }

        public IEnumerable<IRoom> Rooms { get; }

        public IRoom SelectedRoom
        {
            get
            {
                return selectedRoom;
            }

            set
            {
                if (value != selectedRoom)
                {
                    selectedRoom = value;
                    OnPropertyChanged(() => SelectedRoom);
                    toggleLightCommand.RaiseCanExecuteChanged();
                }
            }
        }

        public BuildingViewModel(IBuildingRepository buildingRepository)
        {
            filterText = string.Empty;
            resetFilterCommand = new DelegateCommand(ResetFilter, CanResetFilter);
            toggleLightCommand = new DelegateCommand(ToggleLight, CanToggleLight);

            Building = new BuildingInfo(buildingRepository.GetBuilding());
            ICollectionView collectionView = CollectionViewSource.GetDefaultView(Building.Rooms);
            filteredRooms = new CollectionViewSource<IRoom>(collectionView);
            filteredRooms.Filter = FilterRoom;
            Rooms = filteredRooms;
        }

        private bool FilterRoom(object roomObject)
        {
            bool accepted = false;

            if (!string.IsNullOrEmpty(FilterText))
            {
                if (roomObject != null)
                {
                    IRoom room = roomObject as IRoom;
                    if (room != null)
                    {
                        accepted = IsRoomMatchingFilter(room);
                    }
                }
            }
            else
            {
                accepted = true;
            }

            return accepted;
        }

        private bool IsRoomMatchingFilter(IRoom room)
        {
            return room.Id.ToString(CultureInfo.InvariantCulture).Contains(FilterText) || room.Name.Contains(FilterText);
        }

        private void ResetFilter()
        {
            FilterText = string.Empty;
        }

        private bool CanResetFilter()
        {
            return !string.IsNullOrEmpty(filterText);
        }

        private void ToggleLight()
        {
            var room = SelectedRoom;
            if (room.Light == LightState.Off)
            {
                room.Light = LightState.On;
            }
            else
            {
                room.Light = LightState.Off;
            }
        }

        private bool CanToggleLight()
        {
            return SelectedRoom != null;
        }

    }
}
