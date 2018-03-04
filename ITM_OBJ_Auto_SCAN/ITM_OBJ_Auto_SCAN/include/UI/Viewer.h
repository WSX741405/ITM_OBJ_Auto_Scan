#ifndef VIEWER
#define VIEWER

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <vtkRenderWindow.h>

typedef pcl::PointXYZRGBA PointT;

class Viewer
{
public:
	Viewer(std::string title = "") : _title(title)
	{
		_viewer.reset(new pcl::visualization::PCLVisualizer(_title, false));
	}

	void Show(boost::shared_ptr<pcl::PointCloud<PointT>> cloud, std::string name = "")
	{
		if (!_viewer->updatePointCloud(cloud, name))
			_viewer->addPointCloud(cloud, name);
	}

	void Clear()
	{
		_viewer->removeAllPointClouds();
	}

	void SetupInteractor(QVTKInteractor* interactor, vtkRenderWindow* renderWindow)
	{
		_viewer->setupInteractor(interactor, renderWindow);
	}

	vtkRenderWindow* GetRenderWindow()
	{
		return _viewer->getRenderWindow();
	}

	void AddCoordinateSystem(double coorSys)
	{
		_viewer->addCoordinateSystem(coorSys);
	}

private:
	std::string _title;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> _viewer;
};

#endif