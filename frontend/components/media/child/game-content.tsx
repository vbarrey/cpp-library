"use client";

import { Game } from "@/lib/api";
import { motion } from "motion/react";
import { GenresList } from "./genres-list";

type Props = {
    game: Game,
    expanded: boolean,
}

export function GameContent({ game, expanded }: Props) {
    return (
        <div className="min-w-0 flex-1 p-4">
            <h2 className="font-bold truncate">
                {game.title}
            </h2>

            <p className="text-sm text-muted-foreground">
                {game.developer}
            </p>
            
            <GenresList genres={game.genres} />

            {expanded && (

                <motion.div
                    initial={{
                        opacity: 0,
                        y: 10,
                    }}

                    animate={{
                        opacity: 1,
                        y: 0,
                    }}

                    transition={{
                        delay: 0.2,
                    }}
                >

                    <p className="mt-4 text-sm leading-relaxed">
                        {game.description}
                    </p>

                    <p className="mt-4 text-sm leading-relaxed">
                        {game.platform}
                    </p>

                    <p className="mt-4 text-sm leading-relaxed">
                        {game.multiplayer ? "Multiplayer" : "Single player"}
                    </p>
                </motion.div>
            )}

        </div>
    );
}