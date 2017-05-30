using System.Windows;

namespace AkkaTalk
{
    public partial class App : Application
    {
        private void OnStartup(object sender, StartupEventArgs e)
        {
            var bootstrapper = new Bootstrapper();
            bootstrapper.Run();
        }
    }
}
