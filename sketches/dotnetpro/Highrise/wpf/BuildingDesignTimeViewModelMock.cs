using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Windows.Input;

using HighRise.Model;

using Prism.Mvvm;

namespace HighRise.ViewModel
{
    [ExcludeFromCodeCoverage]
    public class BuildingDesignTimeViewModelMock : BindableBase, IBuildingViewModel
    {
        public string FilterText
        {
            get
            {
                return "FooBar";
            }

            set
            {
                throw new NotImplementedException();
            }
        }

        public ICommand ResetFilterCommand => null;

        public ICommand ToggleLightCommand => null;

        public IBuilding Building { get; }

        public IEnumerable<IRoom> Rooms { get; }

        public IRoom SelectedRoom { get; set; }

        public BuildingDesignTimeViewModelMock()
        {
            IBuildingRepository buildingRepository = new BuildingRepositoryMock();
            Building = buildingRepository.GetBuilding();
            Rooms = Building.Rooms;
        }

    }
}
