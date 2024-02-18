# Function to log debug info to console
function print_debug_info {
    param([string]$info)
    Write-Output "$(Get-Date -Format 'yyyy-MM-dd HH:mm:ss') - $info"
}

# Check for the presence of required commands or utilities
function check_command {
    param([string]$cmd, [string]$desc)
    if (Get-Command $cmd -ErrorAction SilentlyContinue) {
        print_debug_info "$desc found at $((Get-Command $cmd).Source)"
    } else {
        print_debug_info "$desc is required but not found. - Not installed"
        return 1
    }
}

# Check for the presence of Visual Studio folder on hard drives
function check_visual_studio {
    # TODO: Implement Visual Studio check (currently in maintenance)
    print_debug_info "Visual Studio check is currently in maintenance as TODO, will be added soon!"
    return 0  # Assume Visual Studio is installed for now
}

Write-Output "Checking your system..."

# Check for the presence of essential commands
check_command "python" "Python 3"

# Check for the presence of Visual Studio folder (maintenance status)
check_visual_studio

Write-Output "Checking complete. You can now compile DEV7 Tools."
