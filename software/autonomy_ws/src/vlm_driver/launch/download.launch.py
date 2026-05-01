"""Launch the model download helper through ros2 run."""

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    """Create the launch description that downloads configured models."""
    pkg = FindPackageShare("vlm_driver")
    default_config = PathJoinSubstitution([pkg, "config", "models.yaml"])

    config_arg = DeclareLaunchArgument("config", default_value=default_config)
    only_arg = DeclareLaunchArgument("only", default_value="")
    model_root_arg = DeclareLaunchArgument("model_root", default_value="")
    token_arg = DeclareLaunchArgument("hf_token", default_value="")

    cmd = [
        "ros2", "run", "vlm_driver", "download_models",
        "--config", LaunchConfiguration("config"),
        "--model-root", LaunchConfiguration("model_root"),
        "--only", LaunchConfiguration("only"),
        "--hf-token", LaunchConfiguration("hf_token"),
    ]

    return LaunchDescription([
        config_arg, only_arg, model_root_arg, token_arg,
        ExecuteProcess(cmd=cmd, output="screen"),
    ])