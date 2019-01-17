let styles: ToDoFooterStyles.definition = [%raw {| require("./ToDoFooter.scss") |}]
let component = ReasonReact.statelessComponent("ToDoFilter")

type filter = ToDoTypes.filter;

let make = (
    ~count: int,
    ~currentFilter: filter,
    ~filter: filter => unit,
    ~hasCompleted,
    ~removeCompleted: unit => unit,
    _children
) => {
    ...component,

    render: _self => {
        let button = filterType => {
            <li>
                <button 
                    className=Cn.make([
                        styles##filter,
                        styles##active->Cn.ifTrue(currentFilter == filterType),
                    ])
                    onClick={ _e => filter(filterType)}
                >{
                    let text = 
                        switch(filterType) {
                        | All => "All" 
                        | Active => "Active"
                        | Completed => "Completed"
                        }
                    ReasonReact.string(text)
                }
                </button>
            </li>
        };

        <div className=styles##wrap>
            <span className=styles##count>
            {switch(count){
            | 0 => { ReasonReact.string("No item left") }
            | 1 => { ReasonReact.string("1 item left") }
            | _ => { ReasonReact.string({j|$count items left|j}) }
            }}
            </span>
            <ul className=styles##filters>
                { button(All) }
                { button(Active) }
                { button(Completed) }
            </ul>
            <button 
                className=Cn.make([
                    styles##removeCompleted,
                    styles##show->Cn.ifTrue(hasCompleted)
                ])
                onClick={ _e => removeCompleted() }
            >
                { ReasonReact.string("Clear Completed") }
            </button>
        </div>
    }
}
