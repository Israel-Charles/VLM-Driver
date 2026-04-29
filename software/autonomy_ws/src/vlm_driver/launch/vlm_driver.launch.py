from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    pkg = FindPackageShare("vlm_driver")
    default_models = PathJoinSubstitution([pkg, "config", "models.yaml"])
    default_params = PathJoinSubstitution([pkg, "config", "vlm_driver.yaml"])

    models_arg = DeclareLaunchArgument("models_config", default_value=default_models)
    params_arg = DeclareLaunchArgument("params", default_value=default_params)
    selected_arg = DeclareLaunchArgument("selected_model", default_value="llava_ov_0_5b")

    node = Node(
        package="vlm_driver",
        executable="vlm_driver_node",
        name="vlm_driver_node",
        output="screen",
        parameters=[
            LaunchConfiguration("params"),
            {
                "models_config": LaunchConfiguration("models_config"),
                "selected_model": LaunchConfiguration("selected_model"),
            },
        ],
        emulate_tty=True,
    )

    return LaunchDescription([models_arg, params_arg, selected_arg, node])