# Version: 0.1
# Author: Miguel Martinez Lopez
# Uncomment the next line to see my email
# print "Author's email: ", "61706c69636163696f6e616d656469646140676d61696c2e636f6d".decode("hex")


import Tkinter as tk
import ttk

import platform


class ScrollingArea(tk.Frame):
    OS = platform.system()
    
    def __init__(self, root, mousewheel_speed = 2, scroll_horizontally=True, scroll_vertically=True):
        if scroll_horizontally==False and scroll_vertically == False:
            raise Exception("No direction for scrolling indicated")
            
        tk.Frame.__init__(self, root, borderwidth=0)
        
        self.activeArea = None
        
        if type(mousewheel_speed) == int:
            self.mousewheel_speed = mousewheel_speed
        else:
            raise Exception("mousewheel_speed must be an integer.")

        _onMouseWheel = lambda event: self.activeArea._onMouseWheel(event) if self.activeArea else None
        
        if self.OS == "Linux" :
            root.bind_all('<4>', _onMouseWheel,  add='+')
            root.bind_all('<5>', _onMouseWheel,  add='+')
        else:
            # Windows and MacOS
            root.bind_all("<MouseWheel>", _onMouseWheel,  add='+')
        
        self.scrollingArea = tk.Canvas(self, background="green")
        self.scrollingArea.grid(row=0, column=0, sticky="nsew")

        self.rowconfigure( 0, weight=1)
        self.columnconfigure(0, weight=1)
        
        self.innerFrame= tk.Frame(self.scrollingArea, background="blue")
        self.innerFrame.pack()
        
        self.scrollingArea.create_window(0, 0, window=self.innerFrame, anchor='nw', tags="inner_frame")
                    
        self.scrollingArea.bind('<Configure>', self._configure_widget)
        
        
        if scroll_vertically:
            self.vscrollbar = ttk.Scrollbar(self, orient=tk.VERTICAL)
            self.vscrollbar._onMouseWheel = self._build_function_onMouseWheel('y')
            
            self.vscrollbar.grid(row=0, column=1,sticky="ns")
        
            self.scrollingArea.configure(yscrollcommand=self.vscrollbar.set)
            self.vscrollbar['command']=self.scrollingArea.yview
        else:
            self.vscrollbar = None
            

        if scroll_horizontally:
            self.hscrollbar = ttk.Scrollbar(self, orient=tk.HORIZONTAL)
            self.hscrollbar._onMouseWheel = self._build_function_onMouseWheel('x')
            
            self.hscrollbar.grid(row=1, column=0, sticky="ew")
            
            self.scrollingArea.configure(xscrollcommand=self.hscrollbar.set)
            
            self.hscrollbar['command']=self.scrollingArea.xview
        else:
            self.hscrollbar = None
            
        self.scrollingArea.bind('<Enter>',lambda event: self._setActiveArea(self.scrollingArea))
        self.scrollingArea.bind('<Leave>', lambda event: self._unsetActiveArea())

        if self.vscrollbar:
            self.main_scrollbar = self.vscrollbar
        else:
            self.main_scrollbar = self.hscrollbar
        
        self.scrollingArea._onMouseWheel = self.main_scrollbar._onMouseWheel

        for scrollbar in (self.hscrollbar, self.vscrollbar):
            if scrollbar is not None:
                scrollbar.bind('<Enter>', lambda event, scrollbar=scrollbar: self._setActiveArea(scrollbar) )
                scrollbar.bind('<Leave>', lambda event: self._unsetActiveArea())

    def _configure_widget(self, event):
        width = max(self.innerFrame.winfo_reqwidth(),self.scrollingArea.winfo_width())
        height = max(self.innerFrame.winfo_reqheight(),self.scrollingArea.winfo_height())
        
        self.scrollingArea.config(scrollregion="0 0 %s %s" % (width, height))
        
        self.scrollingArea.itemconfigure("inner_frame", width=width)
        self.scrollingArea.itemconfigure("inner_frame", height=height)
    
    def _setActiveArea(self, widget):
        self.activeArea = widget

    def _unsetActiveArea(self):
        self.activeArea = None

    def _build_function_onMouseWheel(self, orient):
        view_command = getattr(self.scrollingArea, orient+'view')
        
        if self.OS == 'Linux':
            def onMouseWheel(event):                
                if event.num == 4:
                    view_command("scroll",(-1)*self.mousewheel_speed,"units" )
                elif event.num == 5:
                    view_command("scroll",self.mousewheel_speed,"units" ) 
                
        elif self.OS == 'Windows':
            def onMouseWheel(event):        
                view_command("scroll",(-1)*int((event.delta/120)*self.mousewheel_speed),"units" ) 
        
        elif self.OS == 'Darwin':
            def onMouseWheel(event):        
                view_command("scroll",event.delta,"units" )             
        
        return onMouseWheel


if __name__== '__main__':
    root = tk.Tk()
    
    scrolling_area = ScrollingArea(root)
    scrolling_area.pack(expand=1, fill=tk.BOTH)
    
    for i in range(20):
        rowFrame = tk.Frame(scrolling_area.innerFrame)
        rowFrame.pack()
        for j in range(8):
            tk.Label(rowFrame, text="Label %s, %s" % (str(i), str(j))).pack(side=tk.LEFT)

    root.mainloop()
