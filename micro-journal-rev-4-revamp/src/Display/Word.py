import time
import displayio
from adafruit_display_text import label
import terminalio

# Load writer instance
from Writer.Writer import writer

# Handling internal text buffer for the writerDeck implementation
# This class manages the display of text, cursor, and status in a word processing application
class Word:
    # initialize the parameters
    def __init__(self, display):
        # save the display instance
        self.display = display
        
        # Initialize last save and sleep times
        self.last_save_time = time.monotonic()
        self.last_sleep_time = time.monotonic()
        
        # Font size and dimensions
        self.font_height = 18
        self.font_width = 12
        
        # how manu lines to render
        self.render_lines = 2
        
        # Screen dimensions
        self.screen_width = 160  # Adjust as needed
        self.screen_height = 80  # Adjust as needed
         
        
    # Setup will be called once when the app starts
    # It initializes the display, loads the file, and sets up the initial state
    def setup(self):
        
        # Load file and config if needed
        writer.load_file(writer.file_buffer.file_name or "0.txt")
               
        # Reset last save and sleep times
        self.last_save_time = time.monotonic()
        self.last_sleep_time = time.monotonic()
        
        # Text Area
        group = displayio.Group()        
        
        # create the label
        self.textArea = label.Label(
            font=terminalio.FONT, text="writerDeck", scale=2
        )

        # set label position on the display
        self.textArea.anchor_point = (0, 0)
        self.textArea.anchored_position = (0, 20)

        # add label to group that is showing on display
        self.display.root_group = group
        group.append(self.textArea)

    # House keeping loop
    def loop(self):
        # Check for any changes in the file buffer
        # self.check_saved()

        # Render the display content
        self.render_text()
        
        #self.render_status()
        #self.render_cursor()

    # Render the visible lines of text on the display
    def render_text(self):
        # render only when the screen buffer is updated
        if not writer.pending_screen_buffer_updated:
            return
        
        start_time = time.monotonic()
        # Get lines from screen buffer
        lines = []
        buf = writer.file_buffer.get_buffer()
        sb = writer.screen_buffer
        total_lines = sb.total_line
        
        start_line = max(0, total_lines - self.render_lines +1)
        for i in range(start_line, total_lines+1):
            start = sb.line_position[i]
            length = sb.line_length[i]
            # Extract the line and remove any embedded newlines
            line = buf[start:start+length].replace('\n', '')
            lines.append(line)
        # Only keep the last 5 lines

        # Merge all lines into one string with line breaks
        merged_text = "\n".join(lines)
        self.textArea.text = merged_text
        elapsed = time.monotonic() - start_time
        
        writer.pending_screen_buffer_updated = False
        
        # debug
        # print(f"render_text elapsed: {elapsed:.6f} seconds")
        
        
        
    def check_saved(self):
        # Auto-save after 4 seconds of inactivity
        buffer_size = writer.file_buffer.get_buffer_size()
        now = time.monotonic()
        if hasattr(self, 'last_buffer_size'):
            if self.last_buffer_size != buffer_size:
                self.last_save_time = now
                self.last_buffer_size = buffer_size
        else:
            self.last_buffer_size = buffer_size

        if now - self.last_save_time > 4:
            self.last_save_time = now
            if not writer.saved:
                writer.save_file()
    

    def render_status(self):
        # Render a simple status bar at the bottom
        group = self.display.groups[0] if self.display.groups else displayio.Group()
        status_text = f"Saved: {'Yes' if writer.saved else 'No'} | Size: {writer.file_buffer.get_buffer_size()}"
        status_area = label.Label(
            terminalio.FONT,
            text=status_text,
            color=0x00FF00 if writer.saved else 0xFF0000,
            x=2,
            y=self.statusbar_y if self.statusbar_y < self.screen_height else self.screen_height - self.font_height
        )
        group.append(status_area)
        self.display.show(group)

    def render_cursor(self):
        # Render a blinking cursor at the current position
        # This is a simple implementation; you may want to draw a rectangle or line
        now = time.monotonic()
        blink = int(now * 2) % 2 == 0  # Blink every 0.5s
        if not blink:
            return

        sb = writer.screen_buffer
        fb = writer.file_buffer
        cursor_line = getattr(fb, 'cursor_line', 0)
        cursor_line_pos = getattr(fb, 'cursor_line_pos', 0)
        x = 2 + cursor_line_pos * self.font_width
        y = 2 + cursor_line * self.font_height

        # Draw a simple rectangle as cursor
        # You may need to use a TileGrid or custom drawing for this
        # For now, just print position for demonstration
        print(f"Cursor at ({x},{y})")

