#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>

struct wl_display *display = NULL;
struct wl_registry *registry = NULL;
struct wl_compositor *compositor = NULL;
struct wl_surface *surface = NULL;
struct wl_shell *shell = NULL;
struct wl_shell_surface *shell_surface = NULL;

static void registry_handle_global(void *data, struct wl_registry *registry,
				   uint32_t name, const char *interface, uint32_t version)
{
	printf("Interface: %s (Version: %d)\n", interface, version);

	if (strcmp(interface, "wl_compositor") == 0) {
		compositor = wl_registry_bind(registry, name, &wl_compositor_interface, 1);
	} else if (strcmp(interface, "wl_shell") == 0) {
		shell = wl_registry_bind(registry, name, &wl_shell_interface, 1);
	}
}

static void registry_handle_global_remove(void *data, struct wl_registry *registry,
					  uint32_t name)
{
}

static const struct wl_registry_listener registry_listener = {
	.global = registry_handle_global,
	.global_remove = registry_handle_global_remove,
};

static void shell_surface_ping(void *data, struct wl_shell_surface *shell_surface,
			       uint32_t serial)
{
	wl_shell_surface_pong(shell_surface, serial);
}

static const struct wl_shell_surface_listener shell_surface_listener = {
	.ping = shell_surface_ping,
};

int main(int argc, char **argv)
{
	/* 1. connect to Wayland server */
	display = wl_display_connect(NULL);
	if (!display) {
		fprintf(stderr, "Failed to connect to Wayland display\n");
		return EXIT_FAILURE;
	}

	/* 2. get registry and register listener */
	registry = wl_display_get_registry(display);
	wl_registry_add_listener(registry, &registry_listener, NULL);

	/* 3. sync requese, wait registry event */
	wl_display_roundtrip(display);

	/* check */
	if (!compositor || !shell) {
		fprintf(stderr, "Missing required Wayland interfaces\n");
		wl_display_disconnect(display);
		return EXIT_FAILURE;
	}

	/* 4. create surface and shell surface */
	surface = wl_compositor_create_surface(compositor);
	shell_surface = wl_shell_get_shell_surface(shell, surface);
	wl_shell_surface_add_listener(shell_surface, &shell_surface_listener, NULL);
	wl_shell_surface_set_title(shell_surface, "Hello Wayland");

	/* 5. set surface type to toplevel */
	wl_shell_surface_set_toplevel(shell_surface);

	printf("Wayland client running. Press Enter to exit...\n");
	getchar();

	/* 6. clean */
	if (shell_surface) wl_shell_surface_destroy(shell_surface);
	if (surface) wl_surface_destroy(surface);
	if (shell) wl_shell_destroy(shell);
	if (compositor) wl_compositor_destroy(compositor);
	if (registry) wl_registry_destroy(registry);
	if (display) wl_display_disconnect(display);

	return EXIT_SUCCESS;
}
