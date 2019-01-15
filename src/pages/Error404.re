let component = ReasonReact.statelessComponent("Error404")

let make = (_children) => {
    ...component,

    render: _self => {
        <div>
            { ReasonReact.string("Page Not Found") }
        </div>
    }
}
